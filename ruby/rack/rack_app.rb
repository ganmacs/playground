rack_conteclass A
  def initialize(app)
    @app = app
  end

  def call
    @app.call
    p 'called in A'
  end
end

class B
  def initialize(app)
    @app = app
  end

  def call
    @app.call
    p 'called in B'
  end
end

class R
  def call
    p [200, 'content-body']
  end
end


app = A.new(
  B.new(R.new)
)

app.call
