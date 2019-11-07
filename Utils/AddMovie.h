#ifndef addMovie_h
#define addMovie_h

#include <stdio.h>

#endif /* addMovie_h */

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void AddMovieName(struct filme);

void AddMovieRelease(struct filme);

void AddMovieDuration(struct filme);

void MovieList(void);

void MovieConfirmation(struct filme);
