defmodule BasketballWebsite do
  # def extract_from_path(data, path) do
  #   Enum.reduce(String.split(path, "."), data, fn k, acc -> acc[k] end)
  # end

  def extract_from_path(data, ""), do: data

  def extract_from_path(data, path) do
    [key | rest] = String.split(path, ".")
    extract_from_path(data[key], Enum.join(rest, "."))
  end

  def get_in_path(data, path) do
    get_in(data, String.split(path, "."))
  end
end
