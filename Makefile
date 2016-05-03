hdrs = myipc.h
opts = -g -c
c_src = customer.c myipc.c
c_obj = customer.o myipc.o
b_src = barber.c myipc.c
b_obj = barber.o myipc.o

all: barber customer

customer: $(c_obj)
	gcc $(c_obj) -o customer
customer.o: $(c_src) $(hdrs)
	gcc $(opts) $(c_src)

barber: $(b_obj)
	gcc $(b_obj) -o barber
barber.o: $(b_src) $(hdrs)
	gcc $(opts) $(b_src)

clean:
	rm customer barber *.o
