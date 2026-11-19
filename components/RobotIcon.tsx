import { useId } from "react";
import { colourFor } from "@/lib/presets";

// Each robot type gets its own silhouette and details, drawn on a 40x40 grid.
// Body parts are shaded with a gradient so they read as solid metal.

type Head = "box" | "dome" | "spikes" | "crown";
type Eyes = "pair" | "single" | "visor";

interface Spec {
  head: Head;
  eyes: Eyes;
  tracks?: boolean;
  cannons?: boolean;
  antenna?: boolean;
  halo?: boolean;
  ridge?: boolean;
  jaw?: boolean;
  brows?: boolean;
  turret?: boolean;
}

const SPECS: Record<string, Spec> = {
  RoboCop: { head: "box", eyes: "visor", ridge: true },
  Terminator: { head: "box", eyes: "single", jaw: true },
  "T-RoboCop": { head: "box", eyes: "visor", ridge: true, cannons: true },
  BlueThunder: { head: "box", eyes: "pair", cannons: true },
  Madbot: { head: "spikes", eyes: "pair", brows: true },
  RoboTank: { head: "box", eyes: "pair", tracks: true, turret: true },
  UltimateRobot: { head: "crown", eyes: "pair" },
  Sentinel: { head: "dome", eyes: "pair", antenna: true },
  PrimeSentinel: { head: "dome", eyes: "single", antenna: true, halo: true },
};

const DEFAULT_SPEC: Spec = { head: "box", eyes: "pair" };
const INK = "#0b0b0d";
const EYE_GLOW = "#ffffff";

// Mix a hex colour towards white (amt > 0) or black (amt < 0).
function shade(hex: string, amt: number): string {
  const n = parseInt(hex.replace("#", ""), 16);
  const ch = [(n >> 16) & 255, (n >> 8) & 255, n & 255].map((v) => {
    const target = amt >= 0 ? 255 : 0;
    return Math.round(v + (target - v) * Math.abs(amt));
  });
  return `rgb(${ch[0]},${ch[1]},${ch[2]})`;
}

interface Props {
  type: string;
  size?: number | string;
}

export function RobotIcon({ type, size = 32 }: Props) {
  const spec = SPECS[type] ?? DEFAULT_SPEC;
  const c = colourFor(type);
  const raw = useId().replace(/[^a-zA-Z0-9_-]/g, "");
  const body = `url(#${raw}-body)`;
  const light = shade(c, 0.35);
  const dark = shade(c, -0.35);

  return (
    <svg
      width={size}
      height={size}
      viewBox="0 0 40 40"
      aria-hidden="true"
      style={{ display: "block", overflow: "visible" }}
    >
      <defs>
        <linearGradient id={`${raw}-body`} x1="0" y1="0" x2="0" y2="1">
          <stop offset="0" stopColor={light} />
          <stop offset="0.55" stopColor={c} />
          <stop offset="1" stopColor={dark} />
        </linearGradient>
        <radialGradient id={`${raw}-glow`}>
          <stop offset="0" stopColor={c} stopOpacity="0.9" />
          <stop offset="1" stopColor={c} stopOpacity="0" />
        </radialGradient>
      </defs>

      {/* back layer: antenna, halo, spikes, crown */}
      {spec.antenna && (
        <g>
          <line x1="20" y1="7" x2="20" y2="2.5" stroke={INK} strokeWidth={2.2} />
          <line x1="20" y1="7" x2="20" y2="2.5" stroke={light} strokeWidth={1} />
          <circle cx="20" cy="2" r="2.2" fill={c} stroke={INK} strokeWidth={0.8} />
          <circle cx="19.3" cy="1.3" r="0.7" fill="#ffffff" stroke="none" />
        </g>
      )}
      {spec.halo && (
        <ellipse cx="20" cy="0.6" rx="10" ry="1.7" fill="none" stroke="#fde68a" strokeWidth={1.4} />
      )}
      {spec.head === "spikes" && (
        <polygon
          points="10,10 7.5,3 14.5,7.5 20,1.5 25.5,7.5 32.5,3 30,10"
          fill={body}
          stroke={INK}
          strokeWidth={1.1}
          strokeLinejoin="round"
        />
      )}
      {spec.head === "crown" && (
        <polygon
          points="10,10 9.5,3.5 15,7 20,1.5 25,7 30.5,3.5 30,10"
          fill={body}
          stroke={INK}
          strokeWidth={1.1}
          strokeLinejoin="round"
        />
      )}

      {/* head */}
      {spec.head === "dome" ? (
        <path
          d="M9.5 20 V16 A10.5 10 0 0 1 30.5 16 V20 Z"
          fill={body}
          stroke={INK}
          strokeWidth={1.1}
        />
      ) : (
        <rect x="10" y="7" width="20" height="13" rx="4" fill={body} stroke={INK} strokeWidth={1.1} />
      )}
      {spec.head !== "dome" && (
        <rect x="10.8" y="7.8" width="18.4" height="3.2" rx="1.6" fill="#ffffff" fillOpacity="0.25" stroke="none" />
      )}
      {spec.head === "dome" && (
        <ellipse cx="15.5" cy="11.5" rx="3" ry="1.8" fill="#ffffff" fillOpacity="0.35" stroke="none" />
      )}

      {/* face panel */}
      {spec.head === "dome" ? (
        <rect x="12" y="13.5" width="16" height="5" rx="2.2" fill={INK} fillOpacity="0.7" stroke="none" />
      ) : (
        <rect x="12.5" y="10" width="15" height="8.5" rx="2.2" fill={INK} fillOpacity="0.7" stroke="none" />
      )}

      {/* eyes */}
      {spec.eyes === "pair" && (
        <g>
          {[16.5, 23.5].map((x) => (
            <g key={x}>
              <circle cx={x} cy="14.2" r="2.8" fill={`url(#${raw}-glow)`} stroke="none" />
              <circle cx={x} cy="14.2" r="1.5" fill={EYE_GLOW} stroke="none" />
            </g>
          ))}
        </g>
      )}
      {spec.eyes === "single" && (
        <g>
          <circle cx="20" cy="14.2" r="4" fill="#ff3b30" fillOpacity="0.35" stroke="none" />
          <circle cx="20" cy="14.2" r="2.2" fill="#ff3b30" stroke="none" />
          <circle cx="19.3" cy="13.5" r="0.6" fill="#ffffff" stroke="none" />
        </g>
      )}
      {spec.eyes === "visor" && (
        <g>
          <rect x="13" y="11.5" width="14" height="4.5" rx="1.2" fill={INK} stroke="none" />
          <rect x="13.8" y="12.2" width="12.4" height="1" rx="0.5" fill="#ffffff" fillOpacity="0.75" stroke="none" />
        </g>
      )}
      {spec.brows && (
        <g stroke={INK} strokeWidth={1.4} strokeLinecap="round">
          <line x1="14.5" y1="10.6" x2="18.2" y2="11.6" />
          <line x1="25.5" y1="10.6" x2="21.8" y2="11.6" />
        </g>
      )}
      {spec.jaw && <rect x="13.5" y="18" width="13" height="2.2" rx="1" fill={INK} stroke="none" />}
      {spec.ridge && <rect x="12" y="6" width="16" height="1.6" rx="0.8" fill={INK} stroke="none" />}

      {/* neck */}
      <rect x="17" y="19.5" width="6" height="2.5" rx="1" fill={INK} stroke="none" />

      {/* torso */}
      <rect x="10" y="21" width="20" height="12" rx="3" fill={body} stroke={INK} strokeWidth={1.1} />
      <rect x="13" y="23.2" width="14" height="6" rx="1.5" fill={INK} fillOpacity="0.55" stroke="none" />
      {[16.2, 20, 23.8].map((x, i) => (
        <circle key={x} cx={x} cy="26.2" r="1" fill={i === 1 ? "#fde68a" : c} stroke="none" />
      ))}
      <rect x="10.6" y="21.6" width="18.8" height="1.2" rx="0.6" fill="#ffffff" fillOpacity="0.3" stroke="none" />

      {/* arms */}
      <rect x="5.5" y="21.5" width="4.5" height="11" rx="2.2" fill={body} stroke={INK} strokeWidth={1.1} />
      <rect x="30" y="21.5" width="4.5" height="11" rx="2.2" fill={body} stroke={INK} strokeWidth={1.1} />
      <circle cx="7.7" cy="33" r="1.6" fill={INK} stroke="none" />
      <circle cx="32.3" cy="33" r="1.6" fill={INK} stroke="none" />

      {/* shoulder cannons */}
      {spec.cannons && (
        <g>
          <rect x="0.5" y="21.8" width="8" height="5" rx="2" fill={INK} stroke="none" />
          <circle cx="0.9" cy="24.3" r="1.5" fill={c} stroke="none" />
          <rect x="31.5" y="21.8" width="8" height="5" rx="2" fill={INK} stroke="none" />
          <circle cx="39.1" cy="24.3" r="1.5" fill={c} stroke="none" />
        </g>
      )}

      {/* turret */}
      {spec.turret && (
        <g>
          <rect x="19.5" y="17.5" width="11" height="2.6" rx="1" fill={INK} stroke="none" />
          <circle cx="20" cy="21" r="3.6" fill={body} stroke={INK} strokeWidth={1.1} />
        </g>
      )}

      {/* legs or tracks */}
      {spec.tracks ? (
        <g>
          <rect x="4" y="31" width="32" height="7.5" rx="3.75" fill={INK} stroke="none" />
          {[8, 14, 20, 26, 32].map((x) => (
            <circle key={x} cx={x} cy="34.75" r="1.6" fill={c} stroke="none" />
          ))}
        </g>
      ) : (
        <g>
          <rect x="13" y="33" width="5" height="5.5" rx="1.5" fill={body} stroke={INK} strokeWidth={1.1} />
          <rect x="22" y="33" width="5" height="5.5" rx="1.5" fill={body} stroke={INK} strokeWidth={1.1} />
          <rect x="11.5" y="37.5" width="8" height="2.5" rx="1.2" fill={INK} stroke="none" />
          <rect x="20.5" y="37.5" width="8" height="2.5" rx="1.2" fill={INK} stroke="none" />
        </g>
      )}
    </svg>
  );
}
