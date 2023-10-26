#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <openssl/md5.h>

#define SECRET_KEY_SIZE 8
#define NUMBER_KEY_MAX_SIZE 8
#define MD5_DIGEST_SIZE 16
#define LEADING_ZEROS 6

typedef char number_key[NUMBER_KEY_MAX_SIZE + 1];
typedef char secret_key[SECRET_KEY_SIZE + 1];
typedef char block_string[NUMBER_KEY_MAX_SIZE + SECRET_KEY_SIZE + 1];

struct block {
	number_key number_key;
	secret_key secret_key;
};

void create_block_string(block_string bs, number_key nk, secret_key sk)
{
	for (int i = 0; i < SECRET_KEY_SIZE; i++)
		bs[i] = sk[i];
		
	for (int i = 0; i < NUMBER_KEY_MAX_SIZE; i++)
		bs[i + SECRET_KEY_SIZE] = nk[i];
}

void validate_secret_key(secret_key *sk, char *secret_key_input)
{
	if (strlen(secret_key_input) != SECRET_KEY_SIZE) {
		perror("Secret key size invalid\n");
		exit(1); 
	}
	(void)strncpy(*sk, secret_key_input, SECRET_KEY_SIZE + 1);
}

void validate_number_key(number_key nk, int number)
{
	(void)sprintf(nk, "%d", number);
}

void compute_md5(block_string bs, char *hash)
{
	unsigned char digest[MD5_DIGEST_SIZE];
	
	MD5_CTX ctx;
	(void)MD5_Init(&ctx);
	(void)MD5_Update(&ctx, bs, strlen(bs));
	(void)MD5_Final(digest, &ctx);

	for (int i = 0, j = 0; i < MD5_DIGEST_SIZE; i++, j+=2)
		(void)sprintf(hash+j, "%02x", digest[i]);
		
	hash[MD5_DIGEST_SIZE * 2] = 0;
}

int validate_hash(char *hash)
{
	if (strlen(hash) != MD5_DIGEST_SIZE * 2) {
		perror("Invalid hash");
		exit(2);
	}

	for (int i = 0; i < LEADING_ZEROS; i++) {
		if (hash[i] != '0')
			return -1;
	}
	return hash[LEADING_ZEROS];
}

void part1(char *secret_key_input)
{
	number_key nk;
	secret_key sk;
	block_string bs;
	validate_secret_key(&sk, secret_key_input);
	
	int counter = 0;
	char hash[MD5_DIGEST_SIZE * 2 + 1];

	do {
		validate_number_key(nk, counter);
		create_block_string(bs, nk, sk);
		compute_md5(bs, &hash);
		counter ++;
	} while (validate_hash(hash) == -1);

	(void)printf("Part1 Answer: %s\n", nk);
}

int main(void)
{
	part1("yzbqklnj");
}
