FROM python:3

RUN mkdir -p /app/authentication
RUN mkdir -p /app/shared
WORKDIR /app

COPY authentication/*.py authentication
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "authentication/app.py"]
