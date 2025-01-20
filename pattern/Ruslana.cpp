#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Класс Рецепт
class Recipe {
private:
    string name;                 // Название рецепта
    vector<string> ingredients;  // Список ингредиентов
    string instructions;         // Инструкции приготовления

public:
    void setName(const string& recipeName) {
        name = recipeName;
    }

    void addIngredient(const string& ingredient) {
        ingredients.push_back(ingredient);
    }

    void setInstructions(const string& recipeInstructions) {
        instructions = recipeInstructions;
    }

    string getName() const {
        return name;
    }

    string getFullRecipe() const {
        string recipe = "Название рецепта: " + name + "\nИнгредиенты:\n";
        for (const auto& ingredient : ingredients) {
            recipe += "- " + ingredient + "\n";
        }
        recipe += "Инструкции:\n" + instructions + "\n";
        return recipe;
    }
};

// Абстрактный строитель
class RecipeBuilder {
protected:
    Recipe recipe;

public:
    virtual ~RecipeBuilder() {}
    virtual void setName() = 0;
    virtual void addIngredients() = 0;
    virtual void setInstructions() = 0;

    Recipe getRecipe() const {
        return recipe;
    }
};

// Конкретные строители
class PancakeRecipeBuilder : public RecipeBuilder {
public:
    void setName() override {
        recipe.setName("Блины");
    }

    void addIngredients() override {
        recipe.addIngredient("Молоко");
        recipe.addIngredient("Яйца");
        recipe.addIngredient("Мука");
        recipe.addIngredient("Сахар");
        recipe.addIngredient("Соль");
    }

    void setInstructions() override {
        recipe.setInstructions("Смешайте все ингредиенты, разогрейте сковороду и выпекайте блины.");
    }
};

class SaladRecipeBuilder : public RecipeBuilder {
public:
    void setName() override {
        recipe.setName("Салат Оливье");
    }

    void addIngredients() override {
        recipe.addIngredient("Картофель");
        recipe.addIngredient("Морковь");
        recipe.addIngredient("Горошек");
        recipe.addIngredient("Яйца");
        recipe.addIngredient("Майонез");
    }

    void setInstructions() override {
        recipe.setInstructions("Нарежьте ингредиенты, смешайте и заправьте майонезом.");
    }
};

// Директор
class RecipeDirector {
public:
    Recipe createRecipe(RecipeBuilder& builder) {
        builder.setName();
        builder.addIngredients();
        builder.setInstructions();
        return builder.getRecipe();
    }
};

// Класс для сохранения рецептов
class RecipeSaver {
public:
    static void saveRecipesToFile(const string& filename, const vector<Recipe>& recipes) {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка при открытии файла для записи!" << endl;
            return;
        }

        for (const auto& recipe : recipes) {
            file << recipe.getFullRecipe() << endl;
            file << "-----------------------" << endl;
        }

        file.close();
        cout << "Рецепты успешно сохранены в файл: " << filename << endl;
    }
};

int main() {
    // Создаем строителей
    PancakeRecipeBuilder pancakeBuilder;
    SaladRecipeBuilder saladBuilder;

    // Директор создает рецепты
    RecipeDirector director;
    vector<Recipe> recipes;
    recipes.push_back(director.createRecipe(pancakeBuilder));
    recipes.push_back(director.createRecipe(saladBuilder));

    // Сохраняем рецепты в файл
    RecipeSaver::saveRecipesToFile("recipes.txt", recipes);

    return 0;
}
