require_relative './section_builder'
require_relative './yaml_loader'
require 'pathname'
require 'logger'
require 'fluent/config'
require 'fluent/config/element'

v = YamlLoader.new.load(Pathname.new('./test.yaml'))
$logger = Logger.new(STDOUT)

class Builder
  def initialize(config)
    @config = config
  end

  def build_and_eval
    evaluate(build)
  end

  def build
    s = system_config_build(@config['system'])
    c = config_build(@config['config'], root: true)
    [s, c]
  end

  def evaluate(configs)
    RootBuilder.new(*configs).to_element
  end

  private

  def system_config_build(config)
    section_build('system', config)
  end

  def config_build(config, indent: 0, root: false)
    sb = SectionBodyBuilder.new(indent, root: root)
    config.each do |c|
      if (lc = c.delete('label'))
        sb.add_section(label_build(lc, indent: indent))
      end

      if (sc = c.delete('source'))
        sb.add_section(source_build(sc, indent: indent))
      end

      if (fc = c.delete('filter'))
        sb.add_section(filter_build(fc, indent: indent))
      end

      if (mc = c.delete('match'))
        sb.add_section(match_build(mc, indent: indent))
      end

      if (wc = c.delete('worker'))
        sb.add_section(worker_build(wc, indent: indent))
      end
    end

    sb
  end

  def label_build(config, indent: 0)
    config = config.dup
    name = config.delete('@name')
    c = config.delete('config')
    SectionStringBuilder.new('label', config_build(c, indent: indent + 2), indent, name)
  end

  def worker_build(config, indent: 0)
    config = config.dup
    num = config.delete('@num')
    c = config.delete('config')
    SectionStringBuilder.new('worker', config_build(c, indent: indent + 2), indent, num)
  end

  def source_build(config, indent: 0)
    section_build('source', config, indent: indent)
  end

  def filter_build(config, indent: 0)
    tag = config.delete('@tag')
    section_build('filter', config, indent: indent, arg: tag)
  end

  def match_build(config, indent: 0)
    config = config.dup
    tag = config.delete('@tag')
    section_build('match', config, indent: indent, arg: tag)
  end

  def section_build(name, config, indent: 0, arg: nil)
    sb = SectionBodyBuilder.new(indent + 2)
    config.each do |key, val|
      if val.is_a?(Array)
        val.each do |v|
          sb.add_section(section_build(key, v, indent: indent + 2))
        end
      elsif val.is_a?(Hash)
        sb.add_section(section_build(key, val, indent: indent + 2, arg: arg))
      else
        sb.add_line(key, val)
      end
    end

    SectionStringBuilder.new(name, sb, indent, arg)
  end
end

puts Builder.new(v).build_and_eval
