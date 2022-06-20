FROM python:3

RUN mkdir -p /app/init_shop_db
RUN mkdir -p /app/shared
WORKDIR /app

COPY init_shop_db/*.py init_shop_db
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "init_shop_db/app.py"]
