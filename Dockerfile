FROM python:3.10.2

WORKDIR /turntable-machine

COPY requirements.txt .

RUN pip install -r requirements.txt

COPY ./src .

CMD ["python", "main.py"]