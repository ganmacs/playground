FROM fluent/fluentd:v1.9-debian

USER root

RUN ["gem", "install", "fluent-plugin-prometheus_pushgateway"]

COPY fluentd fluentd

USER fluent
