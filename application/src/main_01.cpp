#include <iostream>

#include <sw/redis++/redis++.h>

int main(int argc, char** argv) {

    const char *path = argv[ 0 ];

    std::cout << "Current path: " << path << std::endl;

    // ***** REDIS *****
    try {

      auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");

      redis.auth( "12345678" );
      //redis.command("AUTH", "12345678");

      /* initialize random seed: */
      srand (time(NULL));

      /* generate secret number between 1 and 10: */
      int secret = rand() % 10 + 1;

      auto val = redis.get( "key1" );    // val is of type OptionalString. See 'API Reference' section for details.

      //sw::redis::UpdateType type = sw::redis::UpdateType::ALWAYS;

      if ( !val ) {

        redis.set( "key1", std::to_string( secret ), std::chrono::seconds(30));

        val = redis.get( "key1" );

        std::cout << "Key1 (From Set): " << *val << std::endl;

      }
      else {

        // Dereference val to get the returned value of std::string type.
        std::cout << "Key1 (From Cache): " << *val << std::endl;

      }   // else key doesn't exist.

    }
    catch ( const std::exception &ex ) {

      std::cout << ex.what() << std::endl;

    }
    // ***** REDIS *****

    std::cout << "Press enter to exit" << std::endl;

    while ( getchar() != '\n' );

    return 0;
}
