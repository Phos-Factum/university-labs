Switch ($args[0])
{
	-all { 
		Get-Process; 
		Break 
	
	}
	-s {  # поиск по заданному слову
		$param=$args[1]

		echo "Результат по вашему запросу ($param):"
        $ln = (Get-Process | findstr "$param").Length

		if ( $ln -gt 0 )
		{
			Get-Process | select -first 1
		    Get-Process | findstr "$param"
		}
        else
        {
			echo "Ничего не найдено!"
		}
		Break
	}
	-h {	# справка
		echo "Доступный функционал:"
		echo "-all               : Вывод всех процессов"
		echo "-s processname     : Поиск процессов по имени"
		echo "-h                 : Помощь"
		echo "-p processname pri : Изменить приоритет процесса"
		echo "-lib pid       : Просмотр библиотек, используемых процессом"
		echo "-u pid         : Вывести пользователя, запустившего процесс"
		echo "-f pid         : Просмотр файлов, открытых процессом"
		# echo "-c pid         : Вывести значение процессорного времени, используемого процессом"
		echo "-k pid         : Принудительная остановка процесса"
        Break
	}
	"-k" { 	# остановка процесса по PID
		$processid=$args[1]
		Taskkill /PID $processid /F
        Break
	}
	"-p" {	# назначение приоритета по processname
		$processname=$args[1]		
		
		if ( $args[2] -le -1 -or $args[2] -ge 6 )
		{
			echo "Значение приоритета должно находиться в границах от 0 до 5!"
		 	exit
		}
		
		Switch ($args[2])
		{
			5 { # realtime
				$priority = 256
				echo "Установлен приоритет: realtime"
				Break
			}
			4 { # hight
				$priority = 128
				echo "Установлен приоритет: hight"
				Break
			}
			3 { # abovenormal
				$priority = 32768
				echo "Установлен приоритет: abovenormal"
				Break
			}
			2 { # normal
				$priority = 32
				echo "Установлен приоритет: normal"
				Break
			}
			1 { # belownormal
				$priority = 16384
				echo "Установлен приоритет: belownormal"
				Break
			}
			0 { # low
				$priority = 64
				echo "Установлен приоритет: low"
				Break
			}
		}
		
		# установить приоритет
		wmic process where "name='$processname'" call setpriority "$priority" | select -last 0
		
		# вывод приоритета по имени
		wmic process where "name='$processname'" get Priority
		
        Break
		}
	"-lib" {	# вывод библиотек по processname
		$processname=$args[1]
		echo "Библиотеки, используемые $processname :"
		Get-Process -name $processname -Module
        Break
		}
	"-u" {	# вывод имени пользователя по processname
		$processname=$args[1]
		echo "Пользователь, запустивший $processname :"
		Get-WmiObject win32_process|?{$_.name -eq "$processname"}|%{$_.getowner().user}
        Break
		}
	# "-f" { 	# вывод файлов по processname
	#	$processname=$args[1]
	#	echo "Файлы, открытые процессом $processname :"
	#	Get-Process -name $processname 
    #    Break 
    #}
	"-c" { 	# потребление процессорного времени по processname
		$processname=$args[1]
		echo "Потребление процессорного времени процессом $processname :"
		
		Break
		}
}
