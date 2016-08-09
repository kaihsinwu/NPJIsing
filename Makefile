CC := g++
CCFLAG := -O3 -std=c++0x



all : npjising_anneling

#npjising_brute: npjising_brute.cpp
#	$(CC) $(CCFLAG) $^ -o $@

npjising_anneling: npjising_anneling.cpp
	$(CC) $(CCFLAG) $^ -o $@

#npjising_generator: npjising_generator.cpp
#	$(CC) $(CCFLAG) $^ -o $@

.phony: clean
clean :
	rm -rf *.gch npjising_anneling *.o
