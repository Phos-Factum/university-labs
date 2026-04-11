#!/bin/bash
echo "Всего процессов:"
ps axl | wc -l
while [ -n "$1" ]
do
	case "$1" in
	-all) # вывод всех процессов с политикой планирования (с обрезанным CMD)
	echo "PID   PPID  USER       STAT  NI  %CPU  %MEM     TIME     POLICY       CMD"
	while read pid ppid user stat ni cpu mem time cmd; do
		if [[ "$pid" =~ ^[0-9]+$ ]]; then
			policy=$(chrt -p "$pid" 2>/dev/null | grep -o 'SCHED_[A-Z_]*')
			# обрезаем длинную команду до 50 символов
			short_cmd=$(echo "$cmd" | cut -c 1-50)
			printf "%-5s %-5s %-10s %-5s %-3s %-5s %-5s %-10s %-12s %s\n" \
				"$pid" "$ppid" "$user" "$stat" "$ni" "$cpu" "$mem" "$time" "${policy:-N/A}" "$short_cmd"
		fi
	done < <(ps -eo pid,ppid,user,stat,ni,%cpu,%mem,time,cmd --no-headers)
	shift
	;;


	-s)   # поиск по заданному слову
	param=$2
	echo "Результат по вашему запросу ($param):"
	results=$(ps -eo pid,ppid,user,stat,ni,%cpu,%mem,time,cmd --no-headers | grep -i "$param" | grep -v "grep")
	if [ -n "$results" ]; then
		echo "PID   PPID  USER       STAT  NI  %CPU  %MEM     TIME     POLICY       CMD"
		while read pid ppid user stat ni cpu mem time cmd; do
			if [[ "$pid" =~ ^[0-9]+$ ]]; then
				policy=$(chrt -p "$pid" 2>/dev/null | grep -o 'SCHED_[A-Z_]*')
				short_cmd=$(echo "$cmd" | cut -c 1-50)
				printf "%-5s %-5s %-10s %-5s %-3s %-5s %-5s %-10s %-12s %s\n" \
					"$pid" "$ppid" "$user" "$stat" "$ni" "$cpu" "$mem" "$time" "${policy:-N/A}" "$short_cmd"
			fi
		done <<< "$results"
	else
		echo "Ничего не найдено!"
	fi
	shift
	;;

	-h)	# справка
		echo "Доступный функционал:"
		echo "-all           : Вывод всех процессов"
		echo "-s processname : Поиск процессов по имени"
		echo "-h             : Помощь"
		echo "-p pid pri     : Изменить приоритет NICE  процесса"
		echo "-lib pid       : Просмотр библиотек, используемых процессом"
		echo "-u pid         : Вывести пользователя, запустившего процесс"
		echo "-f pid         : Просмотр файлов, открытых процессом"
		echo "-c pid         : Вывести значение процессорного времени, используемого процессом"
		echo "-schp pid      : Просмотр политики планирования у процесса"
		echo "-fifo pid pri  : Установить политику планирования SHRED_FIFO и изменить приоритет"
		echo "-r pid pri     : Установить политику планирования SHRED_RR и изменить приоритет"
		echo "-o pid         : Установить политику планирования SHRED_OTHER"
		echo "-b pid         : Установить политику планирования SHRED_BATCH"
		echo "-i pid         : Установить политику планирования SHRED_IDLE"
		echo "-d pid         : Установить политику планирования SHRED_DEADLINE"
		echo "-k pid         : Остановка процесса"
		;;
	-k) 	# остановка процесса по PID
		processid=$2
		kill $processid
		;;
	-p)	# назначение приоритета по PID
		processid=$2
		priority=$3
		if [[ "$priority" -lt -20 || "$priority" -gt 20 ]]
		then
			echo "Значение приоритета должно находиться в границах от -20 до 20!"
			exit
		fi
		curr=$(ps -o ni -p $2 | tail -n 1)
		echo "Текущий приоритет ID$2: $curr"
		if [ "$priority" -lt "$curr" ]
		then
			sudo renice -n $priority $processid
		else
			renice -n $priority $processid
		fi
		shift
		shift
		;;
	-lib)	# вывод библиотек по PID
		processid=$2
		echo "Библиотеки, используемые ID$processid:"
		pldd $processid
		shift
		;;
	-u)	# вывод имени пользователя по PID
		processid=$2
		echo "Пользователь, запустивший ID$processid:"
		ps -o user -p $processid | tail -n 1
		shift
		;;
	-f) 	# вывод файлов по PID
		processid=$2
		echo "Файлы, открытые процессом ID$processid:"
		lsof -p $processid | tr -s ' ' | cut -d' ' -f 9 | tail -n +2
		shift ;;
	-c) 	# потребление процессорного времени по PID
		processid=$2
		echo "Потребление процессорного времени процессом ID$processid:"
		echo "$(ps -o %cpu -p $processid | tail -n 1)%"
		shift
		;;
	-schp)	# вывод политики планирования и приоритета по PID
		processid=$2
		echo "Текущая политика планирования процесса ID$processid:"
		chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE'
		shift
		;;
	-fifo)  # установка политики планирования SHRED_FIFO и изменение приоритета
		processid=$2
		priority=$3
		if [[ "$priority" -lt 1 || "$priority" -gt 99 ]]
		then
			echo "Значение приоритета должно находиться в границах от 1 до 99!"
			exit
		fi
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		sudo chrt -f -p $priority $processid
		newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"
		shift
		;;
	-r)     # установка политики планирования SHRED_RR и изменение приоритета"
		processid=$2
		priority=$3
		if [[ "$priority" -lt 1 || "$priority" -gt 99 ]]
		then
			echo "Значение приоритета должно находиться в границах от 1 до 99!"
			exit
		fi
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		sudo chrt -r -p $priority $processid
		newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"
		shift
		;;
	-o)     # установка политики планирования SHRED_OTHER"
		processid=$2
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		sudo chrt -o -p 0 $processid
		newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"
		shift
		;;
	-b)     # установка политики планирования SHRED_BATCH"
		processid=$2
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		sudo chrt -b -p 0 $processid
		newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"
		shift
		;;
	-i)     # установка политики планирования SHRED_IDLE"
		processid=$2
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		sudo chrt -i -p 0 $processid
		newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"
		shift
		;;
	-d)     # установка политики планирования SHRED_DEADLINE"
		processid=$2
		deadline=$3
		sudo chrt -d -D $deadline -p 0 $processid
		oldSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
                sudo chrt -i -p 0 $processid
                newSHP=$(chrt -p $processid | grep -o 'SCHED_OTHER\|SCHED_FIFO\|SCHED_RR\|SCHED_BATCH\|SCHED_IDLE\|SCHED_DEADLINE')
		echo "Политика планирования процесса ID$processid $oldSHP сменилась на $newSHP"	
		shift
		shift
		;;
	esac
	shift
done
