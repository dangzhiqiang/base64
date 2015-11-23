#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

static char find_pos(char ch)
{
	char *ptr = (char*)strrchr(base, ch);
	if (!ptr) {
		fprintf(stderr, "error: source code is not base64 decode, decode dirty\n");
		return 0;
	}
	return (ptr - base);
}

char *base64_encode(const char* data, int data_len)
{
	long int prepare = 0;
	int ret_len;
	int temp = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	char changed[4];
	int i = 0;

	if (data == NULL)
		return NULL;

	ret_len = data_len / 3;
	temp = data_len % 3;

	if (temp > 0) {
		ret_len += 1;
	}
	ret_len = ret_len * 4;
	ret = (char *)malloc(ret_len + 1);
	if (ret == NULL) {
		fprintf(stderr, "%s: failed to allocate memory\n", __func__);
		return NULL;
	}
	memset(ret, 0, ret_len + 1);
	f = ret;
	while (tmp < data_len) {
		temp = 0;
		prepare = 0;
		memset(changed, '\0', 4);
		while (temp < 3) {
			if (tmp >= data_len) {
				break;
			}
			prepare = ((prepare << 8) | (data[tmp] & 0xFF));
			tmp++;
			temp++;
		}
		prepare = (prepare << ((3 - temp) * 8));
		for (i = 0; i < 4; i++) {
			if (temp < i) {
				changed[i] = 0x40;
			} else {
				changed[i] = (prepare >> ((3 - i) * 6)) & 0x3F;
			}
			*f = base[(int)changed[i]];
			f++;
		}
	}
	*f = '\0';
	return ret;
}

char *base64_decode(const char *data, int *length)
{
	int equal_count = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	int temp = 0;
	char need[3];
	long int prepare = 0;
	int i = 0;
	int data_len = 0;
	int ret_len = 0;

	if(data == NULL)
		return NULL;

	data_len = strlen(data);
	if (data_len == 0) {
		*length = 0;
		return NULL;
	} else if (data_len % 4 != 0) {
		*length = 0;
		fprintf(stderr, "error: source code is not base64 decode\n\n");
		return NULL;
	}
	ret_len = (data_len / 4) * 3;

	if (*(data + data_len - 1) == '=') {
		equal_count += 1;
	}
	if (*(data + data_len - 2) == '=') {
		equal_count += 1;
	}
	switch (equal_count) {
	case 1:
		ret_len -= 1;
		break;
	case 2:
		ret_len -= 2;
		break;
	}
	ret = (char *)malloc(ret_len + 1);
	if (ret == NULL) {
		fprintf(stderr, "%s: failed to allocate memory\n", __func__);
		*length = 0;
		return NULL;
	}
	memset(ret, 0, ret_len + 1);
	*length = ret_len;
	f = ret;
	while (tmp < (data_len - equal_count)) {
		temp = 0;
		prepare = 0;
		memset(need, 0, 4);
		while (temp < 4) {
			if (tmp >= (data_len - equal_count)) {
				break;
			}
			prepare = (prepare << 6) | (find_pos(data[tmp]));
			temp++;
			tmp++;
		}
		prepare = prepare << ((4 - temp) * 6);
		for (i=0; i<3 ;i++) {
			if (i == temp - 1) {
				break;
			}
			*f = (char)((prepare>>((2 - i)*8)) & 0xFF);
			f++;
		}
	}
	*f = '\0';
	return ret;
}

int encode(void)
{
	char data[1024];
	char *encode = NULL;
	int len = 0;

	printf("input string to encode：\n");
	scanf("%1023s", data);
	len = strlen(data);

	encode = base64_encode(data, len);	
	if (encode == NULL) {
		printf("error: encode fail\n");
		return -1;
	}

	printf("encode value: %s\n", encode);
	free(encode);

	return 0;
}

int decode(void)
{
	char data[1024];
	char *str_pt = NULL;
	char *decode = NULL;
	int len = 0;

	printf("input string to encode：\n");
	scanf("%1023s", data);
	str_pt = data;

	decode = base64_decode(str_pt, &len);	
	if (decode == NULL) {
		printf("error: decode fail\n");
		return -1;
	}

	printf("encode  value: %s\n", decode);
	printf("encode length: %d\n", len);
	free(decode);

	return 0;
}

void usage(char *self)
{
	printf("Usage:\n");
	printf("\t%s --encode            # encode strings which you input\n", self);
	printf("\t%s --decode            # decode strings which you input\n", self);
	printf("\t%s --help or -h        # show this help infomation\n", self);
}

int main(int argc, char **argv)
{
	if (argc == 2) {
		if (strcmp(argv[1], "--encode") == 0) {
			encode();
		} else if (strcmp(argv[1], "--decode") == 0) {
			decode();
		} else {
			usage(argv[0]);
		}
	} else {
		usage(argv[0]);
	}

	return 0;
}
