// activation_detail.tsx
// (C) Martin Alebachew, 2023

export default function ActivationDetail({field, value}: {field: string, value: string}) {
  return (
    <div>
      <span>{field}</span>
      <span className="pad-left-two-rem">{value}</span>
    </div>
  );
}