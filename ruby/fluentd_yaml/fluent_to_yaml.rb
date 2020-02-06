require 'fluent/config'
require 'fluent/config/parser'
require 'pathname'
require 'yaml'

path = '/Users/yuta.iwama/src/github.com/ganmacs/playground/ruby/fluentd_yaml/test.conf'

r = File.open(path) { |io|
  Fluent::Config.parse(io.read, File.basename(path), File.dirname(path), true)
}

class ToHash
  def initialize
  end

  def build(r)
    config = {
      'system' => {},
      'config' =>  [],
    }

    r.each_element do |e|
      if e.name == 'system'
        config.merge!(handle_section(e, arg_name: nil))
      end
    end

    r.each_element do |e|
      if e.name == 'system'
        next
      end

      case e.name
      when 'source'
        config['config'] << handle_section(e, arg_name: nil)
      when 'match'
        config['config'] << handle_section(e, arg_name: '@tag')
      when 'filter'
        config['config'] << handle_section(e, arg_name: '@tag')
      when 'worker'
        config['config'] << handle_section2(e, arg_name: '@num')
      when 'label'
        config['config'] << handle_section2(e, arg_name: '@name')
      end
    end

    config
  end

  def handle_section2(elem, arg_name:)
    r = {}

    if elem.arg && !elem.arg.empty?
      r[arg_name] = elem.arg
    end

    r['config'] = []

    elem.each_element do |e|
      case e.name
      when 'source'
        r['config'] << handle_section(e, arg_name: nil)
      when 'match'
        r['config'] << handle_section(e, arg_name: '@tag')
      when 'filter'
        r['config'] << handle_section(e, arg_name: '@tag')
      end
    end

    { elem.name => r }
  end

  def handle_section(elem, arg_name: '@tag')
    r = {}
    if arg_name && elem.arg && !elem.arg.empty?
      r[arg_name] = elem.arg
    end

    r.merge!(elem.to_h)

    rr = {}
    elem.elements.each do |e|
      (rr[e.name] ||= []) << (handle_section(e)[e.name])
    end

    { elem.name => r.merge(rr) }
  end
end

v = ToHash.new.build(r)
puts v.to_yaml
