# Use the Plot struct as it is provided
defmodule Plot do
  @enforce_keys [:plot_id, :registered_to]
  defstruct [:plot_id, :registered_to]
end

defmodule CommunityGarden do
  def start(opts \\ []) do
    Agent.start(fn -> %{plots: [], index: 0} end, opts)
  end

  def list_registrations(pid) do
    Agent.get(pid, fn %{plots: plots} -> plots end)
  end

  def register(pid, register_to) do
    # fn 返回一个包含两个元素的元祖(tuple)
    #   第一个是 get 获取的值，就是 get_and_update 的返回值。the first being the value to return (that is, the "get" value)
    #   第二个是新状态 the second one being the new state of the agent.
    Agent.get_and_update(pid, fn %{plots: plots, index: index} ->
      plot = %Plot{plot_id: index + 1, registered_to: register_to}
      {plot, %{plots: [plot | plots], index: index + 1}}
    end)
  end

  def release(pid, plot_id) do
    Agent.cast(pid, fn %{plots: plots} = status ->
      plots = Enum.filter(plots, fn %{plot_id: p} -> p !== plot_id end)
      %{status | plots: plots}
    end)
  end

  def get_registration(pid, plot_id) do
    Agent.get(pid, fn %{plots: plots} ->
      plots
      |> Enum.find(
        {
          :not_found,
          "plot is unregistered"
        },
        fn %{plot_id: p} -> p === plot_id end
      )
    end)
  end
end
