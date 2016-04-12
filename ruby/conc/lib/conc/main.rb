require 'concurrent'

module Conc
  class Main
    class Downloader
      def self.download(video)
        sleep 1; # donwload video from video path
        puts "Complete Download video : #{video.path}"
      end
    end

    class Video
      attr_reader :path

      def initialize(path)
        @path = path
      end

      def download
        Downloader.download(self)
      end
    end

    class Program
      attr_reader :id

      def initialize(options, videos = %w(a b c d))
        @options = options
        @id = options[:id]
        @videos = videos.map { |e| Video.new(e) }
      end

      def setup(time)
        task = Concurrent::Future.execute { sleep time; true }
        task2 = Concurrent::Future.execute { download_videos }
        raise 'Fail to download' if task.value && !task2.complete?
        self
      end

      def broadcast
        puts 'broadcast!!!!'
        sleep 1
        self
      end

      private

      def download_videos
        pool = Concurrent::FixedThreadPool.new(@videos.size)
        @videos.each do |x|
          pool.post do
            x.download
          end
        end
        pool.shutdown
        pool.wait_for_termination
      end
    end

    class Broadcaster
      def self.instance
        @instance ||= new
      end

      def self.register(program, time)
        return unless instance.register(program)
        ts = Concurrent::Future.new { program.setup(time) }
        ts.add_observer(instance)
        ts.execute
      end

      def register(program)
        return false if @jobs.include?(program.id) # && job.started_at.to_i < now
        puts "registered #{program.id}"
        @jobs.add program.id
      end

      def update(time, result, reason)
        if reason
          raise reason
          p reason
        else
          @jobs -= result.broadcast.id
          p @jobs
        end
      end

      private

      def initialize
        @jobs = CCC.new
      end
    end

    class CCC
      def initialize
        @bucket = []
        @mutex = Mutex.new
      end

      def add(other)
        @mutex.synchronize do
          @bucket << other
        end
      end

      def include?(value)
        @mutex.synchronize do
          @bucket.include?(value)
        end
      end

      def delete(other)
        @mutex.synchronize do
          @bucket -= other
        end
      end
    end

    # ------------------ main

    def self.start
      new.start
    end

    def start
      p 'start'

      [Program.new(id: 1),
       Program.new(id: 2),
       Program.new(id: 1),
       Program.new(id: 3)
      ].each do |prog|
        Broadcaster.register prog, 3
      end

      sleep
    end
  end
end
