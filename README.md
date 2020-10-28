# Cryptography Course Design

School of Computer Science, Huazhong University of Science and Technology

in 2018 

## SPN
### Implementation of basic SPN algorithm and cryptanalysis
**File Name：SPN_inital.cpp**

Programming Description：

- Function 1: SPN Encryption

	Input: plaintext

	Output: ciphertext

- Function 2: SPN Decryption

	Input: ciphertext ( F1's output )
	
	output: plaintext ( F1's input )


- Function3、4: Linear Attack, Differential Attack

	Instead of 24 - bit key exhaustion, only 8 - bit keys are obtained

**File Name：SPN_analyse.cpp**

Programming Description：

- Function 1: SPN Encryption

	Input: plaintext

	Output: ciphertext

- Function 2 Linear Attack

	1. Get the 8-bit key and the analysis time

	2. Through method of exhaustion, get 32 key, and the analysis time

- Function 3 Differential Attack

	1. Get the 8-bit key and the analysis time

	2. Through method of exhaustion, get 32 key, and the analysis time


### Implementation of Enhance SPN algorithm

**File Name：SPN_plus.cpp**

Programming Description：

- Input: Two 16-bit hexadecimal Numbers separated by Spaces
	
- Output: 32-bit hexadecimal ciphertext and hexadecimal plaintext separated by empty lines


# RSA
--
**File Name：rsa.cpp**

Programming Description:

- Output:

	Public key e n

	Private key D p Q

	Plaintext m

	Ciphertext C

	Plaintext results in different decryption methods

# Rainbow table
--
**File Name：rainbow.cpp**

The main function in the source program contains two test programs

- Manually enter the test program after the rainbow table is generated

- An automated test program behind the rainbow table
