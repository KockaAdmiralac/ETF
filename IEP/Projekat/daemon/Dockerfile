FROM python:3

RUN mkdir -p /app/daemon
RUN mkdir -p /app/shared
WORKDIR /app

COPY daemon/*.py daemon
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "daemon/app.py"]
