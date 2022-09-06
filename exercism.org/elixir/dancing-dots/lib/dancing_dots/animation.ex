defmodule DancingDots.Animation do
  @type dot :: DancingDots.Dot.t()
  @type opts :: keyword
  @type error :: any
  @type frame_number :: pos_integer

  @callback init(opts) :: {:ok, opts} | {:error, error}
  @callback handle_frame(dot, frame_number, opts) :: dot

  defmacro __using__(_) do
    quote do
      @behaviour DancingDots.Animation
      def init(opts), do: {:ok, opts}
      defoverridable init: 1
    end
  end
end

defmodule DancingDots.Flicker do
  use DancingDots.Animation
  alias DancingDots.Dot

  @impl DancingDots.Animation
  def handle_frame(dot, frame_number, _opts) do
    case rem(frame_number, 4) do
      0 -> %Dot{dot | opacity: dot.opacity / 2}
      _ -> dot
    end
  end
end

defmodule DancingDots.Zoom do
  use DancingDots.Animation

  @impl DancingDots.Animation
  def init([velocity: value] = opts) when is_integer(value) do
    {:ok, opts}
  end

  @impl DancingDots.Animation
  def init(velocity: value),
    do:
      {:error,
       "The :velocity option is required, and its value must be a number. Got: #{inspect(value)}"}

  @impl DancingDots.Animation
  def init(_) do
    {:error, "The :velocity option is required, and its value must be a number. Got: nil"}
  end

  @impl DancingDots.Animation
  def handle_frame(dot, frame_number, opts) do
    %DancingDots.Dot{dot | radius: dot.radius + (frame_number - 1) * opts[:velocity]}
  end
end
