# Use the latest Fedora image as the base
FROM fedora:latest

# Update packages and install gcc, gcc-c++ (for g++), and ncurses development libraries
RUN dnf -y update && \
    dnf -y install gcc gcc-c++ ncurses-devel make cmake git gdb && \
    dnf clean all && \
    rm -rf /var/cache/dnf
    
COPY .rlg327 /root/.rlg327

# Set the default command to bash
CMD ["/bin/bash"]
