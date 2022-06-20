FROM python:3

RUN mkdir -p /app/admin
RUN mkdir -p /app/shared
WORKDIR /app

COPY admin/*.py admin
COPY shared/*.py shared
COPY __init__.py .
COPY requirements.txt .

RUN pip install -r requirements.txt

ENV PYTHONPATH="/app"

ENTRYPOINT ["python", "admin/app.py"]
