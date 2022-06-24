FROM python:3

RUN mkdir -p /app/paradajz
RUN mkdir -p /app/shared
WORKDIR /app

COPY paradajz/*.py paradajz
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "paradajz/app.py"]
