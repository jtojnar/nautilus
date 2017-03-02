FROM base/devel

COPY . /opt/nautilus
WORKDIR /opt/nautilus

RUN pacman -Sy && pacman --noconfirm -S git
USER bin
RUN git clone https://aur@aur.archlinux.org/jhbuild-git.git /bin/jhbuild-git && cd /bin/jhbuild-git && makepkg -si --noconfirm && cd - && rm -rf /bin/jhbuild-git
RUN jhbuild --no-interact sysdeps --install
RUN jhbuild --no-interact build nautilus
