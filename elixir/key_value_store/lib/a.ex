defmodule A do
  def start(state) do
    spawn(fn -> state end)
  end

  def run(state) do
    state
    |> listen
    |> run
  end

  def listen(state) do
    receive do
      {:message_type, value} -> Core.do_work(value)
      {:other_type, value} -> Core.do_other_work(value)
    end
  end
end
