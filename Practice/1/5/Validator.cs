using System;

namespace Valid
{
    public class Validator<T>
    {
        private Predicate<T> _rules;

        private Validator(Predicate<T> rules)
        {
            foreach (Predicate<T> rule in rules.GetInvocationList())
            _rules += rules;
        }

        public static Builder<T> CreateBuilder()
        {
            return new Builder<T>();
        }

        public void Validate(T data)
        {
            foreach (var rule in _rules.GetInvocationList())
            {
                if (!(bool)rule.DynamicInvoke(data))
                    throw new ArgumentException(message: "The object is incorrect");
            }
        }


        public class Builder<T>
        {
            private Predicate<T> _rules;

            public Builder<T> AddRule(Predicate<T> rule)
            {
                _rules += rule;
                return this;
            }

            public Validator<T> GetValidator()
            {
                return new Validator<T>(_rules);
            }
        }
    }
}