FROM python:3

RUN mkdir -p /app/krastavac
RUN mkdir -p /app/shared
WORKDIR /app

COPY krastavac/*.py krastavac
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "krastavac/app.py"]
