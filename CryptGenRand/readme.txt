Compile cryptgenrand.c using gcc like this:

gcc cryptgenrand.c -o cryptgenrand -ltestu01 -lprobdist -lmylib -lwsock32 -lcrypt32

Then run:

.\cryptgenrand > .\cryptgenrand.txt

To generate result:

php analyze_testu01.php ./cryptgenrand.txt

