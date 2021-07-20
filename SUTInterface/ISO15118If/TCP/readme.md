<!-- - configuration	for	usage	of	security	(TCP/TLS);
- configuration	for	cipherSuite;
- configuration	for	TLS	protocol	version;	and
- configuration	for	TLS	certificate. -->

constructor: required service layer handler
- configuration	for	IP	address	and	port : setSUTAddress
- control	for	TCP/TLS	port	disconnection	handling: connect, disconnect
- control	for	receiving	information/status	on	a	given	TCP/TLS	connection: send, sendAsync, receive, receiveAsync,
- notification	of	TCP/TLS	connection	status	events: onConnect, onDisconnect