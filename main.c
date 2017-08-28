#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

#ifdef __ANDROID__
  #include <cutils/properties.h>
  #include <log/log.h>
#endif

#define _XOPEN_SOURCE 500
#include <ftw.h>

static off_t total = 0;

static int sum(const char *fpath, const struct stat *sb, int typeflag,
	       struct FTW *ftwbuf)
{
	// if (typeflag != FTW_NS) // Unnecessary check
	total += sb->st_size;
	return 0;
}

int main(int argc, char **argv)
{
	struct statvfs fsstat;
#ifdef __ANDROID__
	char prop[20];
#endif

	if (!argv[1] || access(argv[1], R_OK)) {
		return 1;
	}
	if (nftw(argv[1], &sum, 1, 1 | 2)) {
		perror("nftw");
		return 2;
	}

	printf("reported size: %ld\n", total);
#ifdef __ANDROID__
	sprintf(prop, "%ld", total);
	property_set("sys.size.real", prop);
#endif

	statvfs(argv[1], &fsstat);

	printf("partition size: %lu\n", fsstat.f_bsize * (fsstat.f_blocks - fsstat.f_bfree));

	return 0;
}
