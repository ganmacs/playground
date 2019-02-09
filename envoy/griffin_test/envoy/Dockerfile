FROM envoyproxy/envoy:v1.9.0

COPY envoy_config.yaml /config.yaml

CMD ["envoy", "-c", "config.yaml", "--v2-config-only"]
# CMD ["envoy", "-c", "config.yaml", "--v2-config-only", "--log-level", "debug"]
