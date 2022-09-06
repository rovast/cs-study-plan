defmodule KitchenCalculator do
  def get_volume({_, v}), do: v

  def to_milliliter({unit, v}) do
    {:milliliter, factor(unit) * v}
  end

  def from_milliliter({:milliliter, v}, unit) do
    {unit, v / factor(unit)}
  end

  def convert(volume_pair, unit) do
    volume_pair
    |> to_milliliter()
    |> from_milliliter(unit)
  end

  defp factor(unit) do
    case unit do
      :cup -> 240
      :fluid_ounce -> 30
      :teaspoon -> 5
      :tablespoon -> 15
      :milliliter -> 1
      _ -> :error
    end
  end
end
