FROM python:3

RUN mkdir -p /app/customer
RUN mkdir -p /app/shared
WORKDIR /app

COPY customer/*.py customer
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "customer/app.py"]
