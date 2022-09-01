defmodule Calculator do
  alias Calculator.Boundary

  @spec start(any) :: pid
  def start(initital_state) do
    Boundary.start(initital_state)
  end

  def add(calculator, n), do: send(calculator, {:add, n})
  def subtract(calculator, n), do: send(calculator, {:subtract, n})
  def multiply(calculator, n), do: send(calculator, {:multiply, n})
  def divide(calculator, n), do: send(calculator, {:divide, n})

  def clear(calculator, n), do: send(calculator, {:clear, n})

  def state(calculator) do
    send(calculator, {:state, self()})

    receive do
      {:state, state} ->
        state
    after
      5000 -> {:error, :timeout}
    end
  end
end
