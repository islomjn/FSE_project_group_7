
FROM ubuntu:22.04
WORKDIR /
RUN mkdir /data/
RUN mkdir /app
COPY * /app/
RUN chmod +x /app/prereqs.sh
RUN ./app/prereqs.sh

ENTRYPOINT ["bash"]

