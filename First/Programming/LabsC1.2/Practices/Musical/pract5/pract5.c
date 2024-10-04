// gcc -o pract5.exe pract5.c -IC:/i686-w64-mingw32/include/SDL2 -LC:/i686-w64-mingw32/lib -lSDL2main -lSDL2


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h> // For usleep
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>

#define MAX_FILENAME_LENGTH 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BAR_WIDTH 600
#define BAR_HEIGHT 20

// Function to detect MP3 files in a directory
void detect_mp3_files(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    printf("Detected MP3 files:\033[0m\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".mp3") != NULL) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

// Function to select a file
char *select_file(const char *dir_path) {
    char filename[MAX_FILENAME_LENGTH + 1]; // +1 for null terminator
    printf("Enter the name of the file to play: ");
    fgets(filename, sizeof(filename), stdin);

    // Remove trailing newline character if present
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // Check if the file exists
    char *full_path = malloc(strlen(dir_path) + strlen(filename) + 1); // +1 for '/' 
    if (full_path == NULL) {
        perror("malloc");
        return NULL;
    }
    sprintf(full_path, "%s/%s", dir_path, filename);

    if (access(full_path, F_OK) != -1) {
        return full_path;
    } else {
        printf("File not found.\n");
        free(full_path);
        return NULL;
    }
}

// Function to convert seconds to minutes:seconds format
void format_time(int seconds, int *minutes, int *secs) {
    *minutes = seconds / 60;
    *secs = seconds % 60;
}

// Function to display progress bar and track time
void display_progress(float progress, int current_time, int full_time) {
    int bar_width = 50;
    int filled_width = (int)(progress * bar_width);
    int current_mins, current_secs, full_mins, full_secs;

    // Convert seconds to minutes:seconds format for current time and full time
    format_time(current_time, &current_mins, &current_secs);
    format_time(full_time, &full_mins, &full_secs);

    printf("[");
    for (int i = 0; i < filled_width; i++) {
        printf("\033[47m "); // White background color
    }
    printf("\033[0m");
    for (int i = filled_width; i < bar_width; i++) {
        printf(" ");
    }
    printf("] %.0f%% | %02d:%02d / %02d:%02d\n", progress * 100, current_mins, current_secs, full_mins, full_secs);
}

// Function to extract file name from full path
const char *extract_file_name(const char *full_path) {
    const char *file_name = strrchr(full_path, '/');
    if (file_name == NULL) {
        file_name = full_path; // If no '/' found, use full path as file name
    } else {
        file_name++; // Move pointer past the '/'
    }
    return file_name;
}

// Function to calculate the BPM of a music file
double calculate_bpm(const char *file_path) {
    // Load the music file to get its duration
    Mix_Music *music = Mix_LoadMUS(file_path);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return -1; // Error loading music file
    }

    // Get the duration of the music file in milliseconds
    int duration_ms = Mix_MusicDuration(music);

    // Calculate the file size in bits (assuming 8 bits per byte)
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", file_path);
        Mix_FreeMusic(music);
        return -1; // Error opening file
    }
    fseek(file, 0, SEEK_END);
    long file_size_bytes = ftell(file);
    fclose(file);
    long file_size_bits = file_size_bytes * 8;

    // Calculate the bitrate in bps
    double bitrate_bps = (double)file_size_bits / (double)(duration_ms / 1000.0);

    // Free the loaded music file
    Mix_FreeMusic(music);

    return bitrate_bps / 60.0;
}

// Function to move backward in the track by 5 seconds
void rewind_music() {

    int position = Mix_GetMusicPosition(NULL);

    // Move backward by 5 seconds
    position -= 5;

    // Ensure the new position doesn't go below zero
    if (position < 0) {
        position = 0;
    }

    // Rewind the music to the new position
    Mix_RewindMusic();
    Mix_SetMusicPosition((double)position); // Convert position to seconds
}

// Function to move forward in the track by 5 seconds
void forward_music() {

    int position = Mix_GetMusicPosition(NULL);
    int duration = Mix_MusicDuration(NULL);

    // Move forward by 5 seconds
    position += 5;

    // Ensure the new position doesn't exceed the total duration
    if (position > duration) {
        position = duration;
    }

    // Rewind the music to the new position
    Mix_RewindMusic();
    Mix_SetMusicPosition((double)position); // Convert position to seconds
}

// Function to display the dancing man animation
void display_dancing_man_1() {
    printf("   O\n");
    printf("  /|\\\n");
    printf("   |\n");
    printf("  / \\\n");
}

// Function to display the dancing man animation
void display_dancing_man_2() {
    printf("     O\n");
    printf("    \\|/\n");
    printf("     |\n");
    printf("    / \\\n");
}

// Function to display the dancing man animation
void display_dancing_man_3() {
    printf("   O\n");
    printf("  \\|/\n");
    printf("   |\n");
    printf("  / \\\n");
}

// Function to display the dancing man animation
void display_dancing_man_4() {
    printf("     O\n");
    printf("    /|\\\n");
    printf("     |\n");
    printf("    / \\\n");
}

// Function to play the selected file
void play_file(const char *file_path) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = Mix_LoadMUS(file_path);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    Mix_PlayMusic(music, 0);

    
    double bpm = calculate_bpm(file_path);
    const char *file_name = extract_file_name(file_path);
    int dancing_man_keyframe = 0;

    int quit = 0;
    float progress = 0.0;
    while (!quit) {        
        int position = Mix_GetMusicPosition(NULL);
        int duration = Mix_MusicDuration(NULL);

        // Check for keypress using kbhit
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case 32: // Spacebar
                    if (Mix_PausedMusic()) {
                        Mix_ResumeMusic();
                    } else {
                        Mix_PauseMusic();
                    }
                    break;
                case 75: // Left arrow key
                    rewind_music(); // Function to move backward by 5 seconds
                    break;
                case 77: // Right arrow key
                    forward_music(); // Function to move forward by 5 seconds
                    break;
                case 27: // ESC key
                    quit = 1; // Set quit to exit the loop
                    break;
                default:
                    break;
            }
        }

        if (position >= duration) {
            Mix_PlayMusic(music, 0);
            Mix_PauseMusic(); // Pause music if end of track is reached
        }

        progress = (float)position / duration;

        // Clear the console
        system("cls");

        // Display music name
        printf("Now playing: %s\n", file_name);

        // Display BPM
        printf("BPM: %.0f\n", bpm);

        // Display progress bar
        display_progress(progress, position, duration);

        // Display button tooltips
        printf("Controls:\n");
        printf("Spacebar: Play/Pause\n");
        printf("Left Arrow: Rewind 5 seconds\n");
        printf("Right Arrow: Forward 5 seconds\n");
        printf("ESC: Exit\n");

        if (Mix_PausedMusic()) {
            // Music is paused, implement any necessary functionality here
        } else {
            dancing_man_keyframe++;
        }

        switch (dancing_man_keyframe) {
            case 1:
                display_dancing_man_1();
                break;
            case 2:
                display_dancing_man_2();
                break;
            case 3:
                display_dancing_man_3();
                break;
            case 4:
                display_dancing_man_4();
                dancing_man_keyframe = 0;
                break;
            default:
                break;
        }

        // Sleep for a short duration
        SDL_Delay(250);
    }


    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}



int WinMain(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle initialization error
        return 1;
    }

    // Call SDL_main with arguments
    int result = SDL_main(argc, argv);

    // Clean up SDL
    SDL_Quit();

    return result;
}

int SDL_main(int argc, char *argv[]) {
    const char *dir_path = "./music";
    while(1) {
        system("cls");
        detect_mp3_files(dir_path);
        char *selected_file = select_file(dir_path);
        if (selected_file != NULL) {
            play_file(selected_file);
            free(selected_file);
        }
    }

    return 0;
}