# Turntable Machine

turntable machine with python system

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
