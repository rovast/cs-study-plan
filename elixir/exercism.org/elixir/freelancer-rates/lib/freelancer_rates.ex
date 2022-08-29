defmodule FreelancerRates do
  def daily_rate(hourly_rate) do
    hourly_rate * 8 / 1
  end

  def apply_discount(before_discount, discount) do
    before_discount * (100 - discount) / 100
  end

  def monthly_rate(hourly_rate, discount) do
    (daily_rate(hourly_rate) * 22)
    |> apply_discount(discount)
    |> ceil()
  end

  def days_in_budget(budget, hourly_rate, discount) do
    budget / monthly_rate(hourly_rate, discount) * 22 / 1
    |> Float.floor(1)
  end
end
