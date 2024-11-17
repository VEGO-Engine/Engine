FROM alpine:latest

RUN apk --update --no-cache add doxygen graphviz git

COPY entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

WORKDIR /source

ENTRYPOINT ["/entrypoint.sh"]

CMD ["doxygen", "/Doxyfile_copy"]