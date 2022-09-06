defmodule RemoteControlCar do
  @enforce_keys [:nickname]
  defstruct [
    :nickname,
    battery_percentage: 100,
    distance_driven_in_meters: 0
  ]

  def new(nickname \\ "none") do
    # %RemoteControlCar{nickname: nickname}
    %__MODULE__{nickname: nickname}
  end

  def display_distance(%__MODULE__{} = remote_car) do
    "#{remote_car.distance_driven_in_meters} meters"
  end

  def display_battery(%__MODULE__{} = remote_car) do
    case remote_car.battery_percentage do
      0 -> "Battery empty"
      n -> "Battery at #{n}%"
    end
  end

  def drive(%__MODULE__{} = remote_car) do
    case remote_car.battery_percentage do
      0 ->
        remote_car

      n ->
        %{
          remote_car
          | battery_percentage: n - 1,
            distance_driven_in_meters: remote_car.distance_driven_in_meters + 20
        }
    end

    # cond do
    #   remote_car.battery_percentage > 0 ->
    #     remote_car
    #     |> Map.put(:distance_driven_in_meters, remote_car.distance_driven_in_meters + 20)
    #     |> Map.put(:battery_percentage, remote_car.battery_percentage - 1)

    #   true ->
    #     remote_car
    # end
  end
end
