CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

# CLIENT
CNTDIR = client
CLIENT = uchat

# SERVER
SVRDIR = server
SERVER = uchat_server

all: $(SERVER) $(CLIENT)
	mv $(CNTDIR)/$(CLIENT) .
	mv $(SVRDIR)/$(SERVER) .

$(SERVER):
	@$(MAKE) -C $(SVRDIR)

$(CLIENT):
	@$(MAKE) -C $(CNTDIR)

uninstall: clean
	rm $(CLIENT)
	rm $(SERVER)

clean:

reinstall: uninstall all

.PHONY: all clean uninstall reinstall


