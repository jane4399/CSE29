# 🧠 Enigma Machine Simulator – CSE29 PA1

This project is a simplified implementation of the historic **Enigma machine** using the C programming language. It simulates encryption and decryption of messages using rotors, similar to the logic of the original Enigma cipher.

---

## 📁 Project Overview

This program supports:

- Custom rotor selection (from 9 preset options)
- Rotor rotations to scramble the cipher
- Full message encryption and decryption
- Case-insensitive input (all letters converted to uppercase)

---

## 🧠 How It Works

- The Enigma machine uses a series of rotors to substitute characters.
- Each rotor is a permutation of the alphabet.
- The user can choose which rotors to use and how many times to rotate them.
- Encryption transforms a message by passing it through the rotors.
- Decryption reverses the process by rotating in the opposite direction.

---

## 🚀 How to Compile and Run

### 🔧 Compile

```bash
gcc -o enigma enigma.c
