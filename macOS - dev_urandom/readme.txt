Compile dev_urandom.c using gcc like this:

gcc dev_urandom.c -o dev_urandom -ltestu01 -lprobdist -lmylib -lm

Then run:

./dev_urandom > ./dev_urandom.txt

To generate result:

php analyze_testu01.php ./dev_urandom.txt

