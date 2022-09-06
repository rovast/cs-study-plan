defmodule LogLevel do
  def to_label(level, legacy?) do
    cond do
      level == 0 and legacy? == false -> :trace
      level == 1 -> :debug
      level == 2 -> :info
      level == 3 -> :warning
      level == 4 -> :error
      level == 5 and legacy? == false -> :fatal
      true -> :unknown
    end

    # case {level, legacy?} do
    #   {0, false} -> :trace
    #   {1, _} -> :debug
    #   {2, _} -> :info
    #   {3, _} -> :warning
    #   {4, _} -> :error
    #   {5, false} -> :fatal
    #   _ -> :unknown
    # end
  end

  def alert_recipient(level, legacy?) do
    label = to_label(level, legacy?)

    cond do
      label == :error or label == :fatal -> :ops
      label == :unknown and legacy? -> :dev1
      label == :unknown -> :dev2
      true -> false
    end
  end
end
