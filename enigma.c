#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ALPHABET_SIZE 26
#define NUM_ROTORS 8

/* Array of rotors */
const char* enigma_rotors[NUM_ROTORS+1] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //0
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", //1
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", //2
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", //3
    "ESOVPZJAYQUIRHXLNFTGKDCMWB", //4
    "UKLBEPXWJVFZIYGAHCMTONDRQS", //5
    "JPGVOUMFYQBENHZRDKASXLICTW", //6
    "NZJHGRCXMYSWBOUFAIVLPEKQDT", //7
    "FKQHTLXOCBJSPDZRAMEWNIUYGV"  //8
};

/*
 * Convert a space-separated string of rotor indices into
 * an integer array of rotor indices
 *
 * @param rotor_ind_str   Space-separated string of rotor indices
 * @param num_rotors      Number of rotors provided in the string
 * @return                Integer array of rotor indices
 */
int* parse_rotor_indices(char* rotor_ind_str, int num_rotors) {
    // TODO
    int *int_arr = malloc(num_rotors * sizeof(int));
    for(int i = 0; i < strlen(rotor_ind_str); i+=2){
            int_arr[i/2] = rotor_ind_str[i] - '0';
    }
    return int_arr;
}

/*
 * Create a 2D array of integers where
 * each row represents a rotor
 *
 * @param rotors          Integer array of rotor indices
 * @param num_rotors      Number of rotors provided
 * @return                2D array where each row represents a rotor
 */
int** set_up_rotors(int* rotors, int num_rotors) {
    // TODO
    int** rotor_config = malloc(num_rotors * sizeof(int*));
    for(int i = 0; i < num_rotors; i++){
        rotor_config[i] = malloc(ALPHABET_SIZE * sizeof(int));
        int row_indices = rotors[i];
        for(int j = 0; j < ALPHABET_SIZE; j++){
            rotor_config[i][j] = enigma_rotors[row_indices][j] - 'A';
        }
    }
    return rotor_config;
}


/*
 * Rotate each rotor to the right by the
 * given number of rotations
 *
 * @param rotor_config   2D array of rotors
 * @param rotations      Number of rotations
 * @param num_rotors     Number of rotors provided
 */
void rotate_rotors(int** rotor_config, int rotations, int num_rotors) {
    // TODO
    char temp_arr[num_rotors][ALPHABET_SIZE];
    for(int i = 0; i < num_rotors; i++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            temp_arr[i][(j + rotations) % ALPHABET_SIZE] = rotor_config[i][j];
        }
        for(int j = 0; j < ALPHABET_SIZE; j++){
            rotor_config[i][j] = temp_arr[i][j];
        }
     }
}

/*
 * Encrypt the given message
 *
 * @param message        Message to encrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Encrypted message
 */
char* encrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    for(int i1 = 0; i1 < num_rotors; i1++){
        for(int i2 = 0; i2 < strlen(message); i2++){
            if(message[i2] >= 'a' && message[i2] <= 'z'){
            message[i2] = message[i2] - 32;
            }

            if(message[i2] >= 'A' && message[i2] <= 'Z') {
                int location = message[i2] - 'A';
                message[i2] = rotor_config[i1][location] + 'A';
            }
        }
    }

    return message;
}

/*
 * Decrypt the given message
 *
 * @param message        Message to decrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Decrypted message
 */
char* decrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    //for(int i1 = num_rotors - 1; i1 >= 0; i1--){
    for(int i1 = 0; i1 < num_rotors; i1++){

        for(int i2 = 0; i2 < strlen(message); i2++){
            if(message[i2] >= 'a' && message[i2] <= 'z'){
                message[i2] = message[i2] - 32;
            }

            if(message[i2] >= 'A' && message[i2] <= 'Z') {
                int location = message[i2] - 'A';
                //message[i2] = rotor_config[i1][location] + 'A';
                for (int j = 0; j < ALPHABET_SIZE; j++) {
                    if (rotor_config[i1][j] == location) {
                        message[i2] = j + 'A';
                        break;
                    }
                }
                }

         }
     }

     return message;

}

/*
 * Format of command line input:
 * ./enigma e "JAVA" 3 "1 2 4" 0
 *
 *    e    - mode (e for encrypt, d for decrypt)
 * "JAVA"  - message
 *    3    - number of rotors to use
 * "1 2 4" - indices of rotors to use
 *    0    - number of rotations of the rotors
 */
int main(int argc, char* argv[]) {
    // TODO
    if(argc != 6) {  // Need 6 arguments total (including program name)
        return 1;
    }
    char* message = argv[2];
    int num_rotors = atoi(argv[3]);
    char* arr = argv[4];
    int rotations = atoi(argv[5]);
    int* rotor_indices = parse_rotor_indices(arr, num_rotors);

    int** rotor_configs = set_up_rotors(rotor_indices, num_rotors);
    rotate_rotors(rotor_configs, rotations, num_rotors);
    char e_or_d = argv[1][0];
    if(e_or_d == 'e'){
       char* encrypted = encrypt(message, rotor_configs, num_rotors);
        printf("Encrypted message: %s\n", encrypted);
     }else if(e_or_d == 'd'){
       char* decrypted = decrypt(message, rotor_configs, num_rotors);
        printf("Decrypted message: %s\n", decrypted);
     }

    return 0;
}
