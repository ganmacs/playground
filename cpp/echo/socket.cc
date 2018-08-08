ConnectionSocket::ConnectionSocket() {



}

    //     int sockfd, numbytes;
    //     char buf[MAXDATASIZE];
    //     struct hostent *he;
    //     struct sockaddr_in their_addr; /* connector's address information */

    //     if (argc != 2) {
    //         fprintf(stderr,"usage: client hostname\n");
    //         exit(1);
    //     }

    //     if ((he=gethostbyname(argv[1])) == NULL) {  /* get the host info */
    //         herror("gethostbyname");
    //         exit(1);
    //     }

    //     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    //         perror("socket");
    //         exit(1);
    //     }

    //     their_addr.sin_family = AF_INET;      /* host byte order */
    //     their_addr.sin_port = htons(PORT);    /* short, network byte order */
    //     their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    //     bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

    //     if (connect(sockfd, (struct sockaddr *)&their_addr, \
    //                                           sizeof(struct sockaddr)) == -1) {
    //         perror("connect");
    //         exit(1);
    //     }
    //     /* sleep(5); */
	// while (1){
	// 	if (send(sockfd, "Hello, world!\n", 14, 0) == -1)
	// 	      perror("send");
	// 	printf("In loop \n");
	// }
    //     close(sockfd);
