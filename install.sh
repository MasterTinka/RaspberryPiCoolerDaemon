#!/bin/bash
su

directory = $(pwd)

qmake-qt5
make 

mkdir /home/$USER/.services
cd /home/$USER/.services

cp $directory/DaemonCooler ./DaemonCooler

echo -e "#!/bin/bash\n$(pwd)/DaemonCooler" > DaemonCooler.sh

chmod +x DaemonCooler.sh

cd /etc/systemd/system 

echo -e "[Unit]\nDescription = Cooler control\n\n[Service]\nRemainAfterExit=true\nExecStart=/home/$USER/.services/DaemonCooler.sh\nType=oneshot\n\n[Install]\nWantedBy=multi-user.target\n" > DaemonCooler.service

cd /etc
echo -e "# Lines must be written in one piece\npin=4\nmax_temp=50\ninterval=10\nworking_time=600\n" > ./CoolerDaemon.conf

systemctl enable DaemonCooler.service

echo "You could find configuration file in /etc/CoolerDaemon.conf"
echo "Log file is in /tmp/cooler.log"
