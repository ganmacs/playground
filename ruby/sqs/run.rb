# frozen_string_literal: true

require 'aws-sdk-sqs'
require 'logger'
require 'pp'

sqs_client = Aws::SQS::Client.new(
  region: 'ap-northeast-1',
  logger: Logger.new($stdout)
)

stop = false
Signal.trap(:INT) { stop = true }
Signal.trap(:TERM) { stop = true }

queue_url = 'URL'

loop do
  if stop
    logger.info('Stop')
    break
  end

  resp = sqs_client.receive_message(
    queue_url: queue_url,
    max_number_of_messages: 1,
    wait_time_seconds: 2,
  )
  message = resp.messages[0]
  if message
    pp message
  sqs_client.delete_message(queue_url: queue_url, receipt_handle: message.receipt_handle)
  end

  unless stop
    sleep(1)
  end
end
