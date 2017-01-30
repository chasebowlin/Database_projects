SELECT SUM(Food.calories)
FROM Food, User, Food_in_a_meal, Meal
WHERE User.user_id = Meal.user_id 
AND Meal.meal_id = Food_in_a_meal.meal_id
AND Food.food_id = Food_in_a_meal.food_id
AND Meal.date = '2016/11/11'
