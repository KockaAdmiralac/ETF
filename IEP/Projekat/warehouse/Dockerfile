FROM python:3

RUN mkdir -p /app/warehouse
RUN mkdir -p /app/shared
WORKDIR /app

COPY warehouse/*.py warehouse
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "warehouse/app.py"]
