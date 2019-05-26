/**
	TODO - make it automatically allocate the right amount of
	memory, because we don't always know the uncompressed size
	before hand.

	allocate CHUNK at a time
	thehn resize if too big at the end
	reallocate(SIZE + CHUNK)

	at the end
	reallocate(final_size);
*/

#include <myz.h>

int inf(void *source, void **dest, unsigned int compressed_length)
{
	int ret;
	unsigned have;
	z_stream strm;
	//unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	unsigned int position=0;
	unsigned int out_position=0;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;

	ret = inflateInit(&strm);

	if (ret != Z_OK) {
		printf("Failed to init Z\n");
		return ret;
	}

	do {
		int diff = compressed_length - position;
		strm.avail_in = CHUNK;
		if (diff < CHUNK) strm.avail_in = diff;

		if (strm.avail_in == 0) break;
		strm.next_in = &source[position];
		position += strm.avail_in;

		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			switch (ret) {
				case Z_NEED_DICT:
					printf("NEED DICT\n");
					ret = Z_DATA_ERROR;
				case Z_DATA_ERROR:
					printf("DATA ERROR\n");
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return 0;
			}
			have = CHUNK - strm.avail_out;
			/*!!!write out to dest*/
			memcpy(*dest+out_position, out, have);
			out_position += have;

		} while(strm.avail_out == 0);

	} while(ret != Z_STREAM_END);

	//printf("Have %i bytes\n", out_position);

	(void)inflateEnd(&strm);

	/*0 if fail*/
	return (ret==Z_STREAM_END) ? out_position : 0;
	/*Deal with errors*/
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;

	return 0;
}
