// #include "../../assignment-autotest/test/assignment1/username-from-conf-file.h"
#include "../../examples/autotest-validate/autotest-validate.h"
#include "unity.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @return the name of the user from the conf file, or
 * an empty string if not found.  Must be freed by the caller
 */
static inline char *malloc_username_from_conf_file() {
  size_t len = 0;
  // Note: this buffer will be reallocated in getline() as necessary
  char *buffer = (char *)malloc(len + 1);
  buffer[0] = '\0';

  FILE *fp = fopen("conf/username.txt", "r");
  if (fp != NULL) {
    /**
     * See https://man7.org/linux/man-pages/man3/getline.3.html
     */
    ssize_t bytes_read = getline(&buffer, &len, fp);

    // remove whitespace from the end
    while (bytes_read > 0 && !isgraph(buffer[bytes_read - 1])) {
      buffer[bytes_read - 1] = '\0';
      bytes_read--;
    }

    // remove whitespace from the front
    char *start = &buffer[0];
    while (bytes_read > 0 && !isgraph(start[0]) && (++start)[0] != '\0') {
    }
    if (start != buffer) {
      memmove(buffer, start, strlen(start) + 1);
    }

    if (bytes_read < 1) {
      fprintf(stderr, "Could not find username in conf/username.txt\n");
    } else {
      printf("Read %s from conf/username.txt\n", buffer);
    }
  } else {
    fprintf(stderr, "Could not open conf/username.txt for reading\n");
  }
  return buffer;
}

/**
 * This function should:
 *   1) Call the my_username() function in autotest-validate.c to get your hard
 * coded username. 2) Obtain the value returned from function
 * malloc_username_from_conf_file() in username-from-conf-file.h within the
 * assignment autotest submodule at assignment-autotest/test/assignment1/ 3) Use
 * unity assertion TEST_ASSERT_EQUAL_STRING_MESSAGE to verify the two strings
 * are equal.  See the [unity assertion
 * reference](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md)
 */
void test_validate_my_username() {
  /**
   * TODO: Replace the line below with your code here as described above to
   * verify your /conf/username.txt config file and my_username() functions are
   * setup properly
   */
  char *confFileName = malloc_username_from_conf_file();
  const char *myUsername = my_username();
  TEST_ASSERT_EQUAL_STRING_MESSAGE(myUsername, confFileName,
                                   "Username doesn't match");
  free(confFileName);
}
