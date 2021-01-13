In first place, in order to run the codes, you must install ROOT and PYTHIA in your system.

ROOT installation tutorial: https://root.cern/install/

Then, you must install PYTHIA.

PYTHIA installation tutorial: See the PYTHIA 8.2 worksheet avalaible in http://home.thep.lu.se/~torbjorn/pythia83html/Welcome.html

Finally, in order to run the algorithms you have to put the following orders in the terminal shell:

> make mymain02
> ./mymain02 > myout02
 
The same apply to the others codes.

Beware: You have also to modify the ROOT section of the Makefile located in pythia8303/examples as

# ROOT (turn off all warnings for readability).
main91 mymain02: $(PYTHIA) $$@.cc
ifeq ($(ROOT_USE),true)
        $(CXX) $@.cc -o $@ -w $(CXX_COMMON) $(ROOT_LIB)\
         `$(ROOT_CONFIG) --cflags --glibs`
else
        $(error Error: $@ requires ROOT)
endif


