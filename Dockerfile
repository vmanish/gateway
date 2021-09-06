FROM ubuntu
LABEL Maintainer="Manish Verma"

RUN apt-get update &&  apt-get install -y git mosquitto scons build-essential gcc make && \
   DEBIAN_FRONTEND="noninteractive" apt-get install -y  cmake  && \
   apt-get install -y   libssl-dev && apt-get install -y python3-pip && \
   pip install paho-mqtt

RUN git clone https://github.com/eclipse/paho.mqtt.c.git && \
    cd paho.mqtt.c  &&   git checkout v1.3.8  &&\
    cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON  && \
    cmake --build build/ --target install  &&  ldconfig    

RUN git clone https://github.com/eclipse/paho.mqtt.cpp  &&  cd paho.mqtt.cpp    &&\
    cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_SAMPLES=TRUE  && \
    cmake --build build/ --target install   && ldconfig

RUN cd /home/   &&\
    git clone https://github.com/vmanish/gateway.git  && \
    cd gateway  &&    scons

WORKDIR /home/gateway/
