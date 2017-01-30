SELECT Food.type, SUM(Food.calories) AS total_calories
FROM Food, User, Food_in_a_meal, Meal
WHERE User.user_id = 1
AND Meal.meal_id = Food_in_a_meal.meal_id
AND User.user_id = Meal.user_id
AND Food_in_a_meal.food_id = Food.food_id
AND Meal.date >= '2016/11/11'
AND Meal.date <= '2016/11/12'
GROUP BY Food.type