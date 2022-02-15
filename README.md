# Turntable Machine

turntable machine with python system

# Set up in raspberry pi board
```bash
sudo apt-get update
sudo apt install git-all
sudo apt-get install python
sudo apt install python3-pip
git clone https://github.com/welcomehyunseo/turntable-machine.git
pip3 install -r requirements.txt
```

# SSH config for vs code
```
Host admin@192.168.219.108:22
  HostName 192.168.219.108
  User admin
  Port 22
```

# Make virtual environment

```bash
python3 -m venv venv
```

# Activate virtual environment

```bash
venv\Scripts\activate.bat
```

# Exit virtual environment

```bash
deactivate
```

# Docker Build && Run

```bash
docker build -t turntable-machine-app .
docker run turntable-machine-app
```

# How to Push and Pull a Docker Image from Docker Hub

```bash
docker login
docker push [username]/[tagname]
docker pull [username]/[tagname]
```

# Save in image

```bash
docker save [tagname] > [image-name].tar
docker load -i ./[image-name].tar
```
